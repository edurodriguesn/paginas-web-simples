const express = require('express');
const multer = require('multer');
const session = require('express-session');
const sqlite3 = require('sqlite3').verbose();
const path = require('path');
const fs = require('fs');
const mongoose = require('mongoose');
const slugify = require('slugify');
const ejs = require('ejs');

const app = express();
const db = new sqlite3.Database('./db/database.db');

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

// Configuração de Multer para uploads
const storage = multer.diskStorage({
    destination: 'uploads/',
    filename: (req, file, cb) => {
        cb(null, Date.now() + path.extname(file.originalname));
    }
});

const upload = multer({ storage: storage });

// Middleware para analisar o corpo da solicitação
app.use(express.urlencoded({ extended: true }));

// Rotas
app.get('/', (req, res) => {
    db.all("SELECT * FROM conteudos", [], (err, rows) => {
        if (err) {
            throw err;
        }
        res.render('index', { conteudos: rows });
    });
});

app.get('/admin', (req, res) => {
    if (!req.session.loggedIn) {
        return res.redirect('/login');
    }
    res.render('admin');
});

app.post('/admin/conteudos', async (req, res) => {
    try {
        const { title, description, imagePath } = req.body;
        const slug = slugify(title, { lower: true });

        // Salvar o conteúdo no banco de dados
        const newContent = new Content({
            title,
            description,
            imagePath,
            slug
        });
        await newContent.save();

        // Gerar a página HTML usando EJS
        const htmlContent = await ejs.renderFile(
            path.join(__dirname, 'views', 'template.ejs'),
            { content: newContent }
        );

        // Salvar o arquivo HTML na pasta 'public/pages'
        const filePath = path.join(__dirname, 'public', 'jogos', `${slug}.html`);
        fs.writeFileSync(filePath, htmlContent, 'utf8');

        res.redirect('/admin');
    } catch (error) {
        res.status(500).send('Erro ao criar o conteúdo e a página');
    }
});

app.get('/login', (req, res) => {
    res.render('login');  // Renderiza o arquivo 'login.ejs' que deve estar na pasta 'views'
});

app.post('/login', (req, res) => {
    const { username, password } = req.body;
    if (username === 'admin' && password === 'senha123') {
        req.session.loggedIn = true;
        res.redirect('/admin');
    } else {
        res.redirect('/login');
    }
});

app.post('/upload', upload.single('imagem'), (req, res) => {
    if (!req.session.loggedIn) {
        return res.redirect('/login');
    }
    const { titulo, descricao } = req.body;
    const imagem = req.file.filename;

    db.run(`INSERT INTO conteudos (titulo, descricao, imagem) VALUES (?, ?, ?)`,
        [titulo, descricao, imagem], (err) => {
            if (err) {
                return console.log(err.message);
            }
            res.redirect('/');
        });
});
// Serve arquivos estáticos da pasta 'uploads'
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));

// Inicialização do servidor
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Servidor rodando na porta ${PORT}`);
});

// Inicializar o banco de dados e a tabela, se necessário
db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS conteudos (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        titulo TEXT NOT NULL,
        descricao TEXT NOT NULL,
        imagem TEXT NOT NULL
    )`);
});

const contentSchema = new mongoose.Schema({
    title: String,
    description: String,
    imagePath: String,
    slug: String // ou id, para URL amigável
});

const Content = mongoose.model('Content', contentSchema);