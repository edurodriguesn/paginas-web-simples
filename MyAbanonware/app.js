const express = require('express');
const multer = require('multer');
const session = require('express-session');
const sqlite3 = require('sqlite3').verbose();
const path = require('path');
const fs = require('fs');
const slugify = require('slugify');
const ejs = require('ejs');

const app = express();
const upload = multer({ dest: 'uploads/' });
const db = new sqlite3.Database('./db/database.db');

// Middleware para processar o corpo da requisição
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// Configuração de sessão
app.use(session({
    secret: 'secreto123',
    resave: false,
    saveUninitialized: true,
}));

// Configuração para EJS
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

// Middleware para servir arquivos estáticos
app.use(express.static('public'));
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));

// Criar tabelas se não existirem
db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS conteudo (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nome TEXT,
        ano INTEGER,
        plataforma TEXT,
        categoria TEXT,
        desenvolvedores TEXT,
        imagens TEXT
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS plataforma (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nome TEXT UNIQUE
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS categoria (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nome TEXT UNIQUE
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS desenvolvedor (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nome TEXT UNIQUE
    )`);
});

app.get('/', (req, res) => {
    db.all("SELECT * FROM conteudos", [], (err, rows) => {
        if (err) {
            throw err;
        }
        res.render('index', { conteudos: rows });
    });
});

// Rota para renderizar a página de login
app.get('/login', (req, res) => {
    res.render('login');
});

// Rota para processar o login
app.post('/login', (req, res) => {
    const { username, password } = req.body;
    if (username === 'admin' && password === 'senha123') {
        req.session.loggedIn = true;
        res.redirect('/admin');
    } else {
        res.redirect('/login');
    }
});

// Middleware para verificar se o usuário está logado
function isAuthenticated(req, res, next) {
    if (req.session.loggedIn) {
        return next();
    } else {
        res.redirect('/login');
    }
}

// Rota para renderizar a página de admin
app.get('/admin', isAuthenticated, (req, res) => {
    db.all("SELECT * FROM conteudo", (err, conteudos) => {
        if (err) {
            return res.status(500).send('Erro ao carregar os conteúdos');
        }
        res.render('admin', { conteudos });
    });
});

// Rota para excluir um conteúdo
app.post('/admin/conteudos/:id/delete', isAuthenticated, (req, res) => {
    const { id } = req.params;
    db.run("DELETE FROM conteudo WHERE id = ?", [id], (err) => {
        if (err) {
            return res.status(500).send('Erro ao excluir o conteúdo');
        }
        res.redirect('/admin');
    });
});

// Rota para renderizar a página de edição de conteúdo
app.get('/admin/conteudos/:id/edit', isAuthenticated, (req, res) => {
    const { id } = req.params;
    db.get("SELECT * FROM conteudo WHERE id = ?", [id], (err, conteudo) => {
        if (err) {
            return res.status(500).send('Erro ao carregar o conteúdo');
        }
        res.render('edit-content', { conteudo });
    });
});

// Rota para processar a edição de conteúdo
app.post('/admin/conteudos/:id/edit', isAuthenticated, upload.array('imagens'), (req, res) => {
    const { id } = req.params;
    const { nome, ano, plataforma, categoria, desenvolvedores, descricao, linkTitle, linkURL } = req.body;
    const linksExternos = Array.isArray(linkTitle) ? linkTitle.map((titulo, index) => ({ titulo, url: linkURL[index] })) : [{ titulo: linkTitle, url: linkURL }];
    const slug = slugify(nome, { lower: true });

    // Criar pasta com o nome do conteúdo em slug dentro da pasta 'uploads'
    const contentDir = path.join(__dirname, 'uploads', slug);
    if (!fs.existsSync(contentDir)) {
        fs.mkdirSync(contentDir, { recursive: true });
    }

    // Mover imagens para a pasta criada
    const imagens = req.files.map(file => {
        const newFilePath = path.join(contentDir, file.originalname);
        fs.renameSync(file.path, newFilePath);
        return path.relative(__dirname, newFilePath);
    });

    const imagensStr = JSON.stringify(imagens);

    db.run(`UPDATE conteudo SET nome = ?, ano = ?, plataforma = ?, categoria = ?, desenvolvedores = ?, imagens = ? WHERE id = ?`,
        [nome, ano, plataforma, categoria, desenvolvedores, imagensStr, id],
        (err) => {
            if (err) {
                return res.status(500).send('Erro ao atualizar o conteúdo');
            }
            res.redirect('/admin');
        });
});
// Rota para renderizar a página de criação de novo conteúdo
app.get('/admin/conteudos/new', isAuthenticated, (req, res) => {
    res.render('new-content');
});
// Rota para adicionar conteúdo
app.post('/admin/conteudos/new', upload.array('imagens'), (req, res) => {
    try {
        const { nome, ano, plataforma, categoria, desenvolvedores, descricao, linkTitle, linkURL } = req.body;
        const linksExternos = Array.isArray(linkTitle) ? linkTitle.map((titulo, index) => ({ titulo, url: linkURL[index] })) : [{ titulo: linkTitle, url: linkURL }];
        const slug = slugify(nome, { lower: true });

        // Criar pasta com o nome do conteúdo em slug dentro da pasta 'uploads'
        const contentDir = path.join(__dirname, 'uploads', slug);
        if (!fs.existsSync(contentDir)) {
            fs.mkdirSync(contentDir, { recursive: true });
        }

        // Mover imagens para a pasta criada
        const imagens = req.files.map(file => {
            const newFilePath = path.join(contentDir, file.originalname);
            fs.renameSync(file.path, newFilePath);
            return path.relative(__dirname, newFilePath);
        });

        const imagensStr = JSON.stringify(imagens);

        db.run(`INSERT INTO conteudo (nome, ano, plataforma, categoria, desenvolvedores, imagens) VALUES (?, ?, ?, ?, ?, ?)`,
            [nome, ano, plataforma, categoria, desenvolvedores, imagensStr],
            function (err) {
                if (err) {
                    return console.log(err.message);
                }

                const content = { id: this.lastID, nome, ano, plataforma, categoria, desenvolvedores, descricao, linksExternos, imagens };
                ejs.renderFile(
                    path.join(__dirname, 'views', 'template.ejs'),
                    { conteudo: content },
                    (err, htmlContent) => {
                        if (err) {
                            console.log('Erro ao renderizar o template:', err);
                            res.status(500).send('Erro ao criar a página HTML');
                        } else {
                            const filePath = path.join(__dirname, 'public', 'pages', `${slug}.html`);
                            fs.writeFileSync(filePath, htmlContent, 'utf8');
                            res.redirect('/admin');
                        }
                    }
                );
            });
    } catch (error) {
        res.status(500).send('Erro ao criar o conteúdo e a página');
    }
});

// Inicialização do servidor
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Servidor rodando na porta ${PORT}`);
});