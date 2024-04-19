const readline = require('readline');

// Criar uma interface de leitura e escrita
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// Perguntar e ler o valor de A
rl.question('Digite o valor de A: ', (valorA) => {
  // Perguntar e ler o valor de B
  rl.question('Digite o valor de B: ', (valorB) => {
    // Converter os valores para inteiros
    const A = parseInt(valorA);
    const B = parseInt(valorB);

    // Calcular a soma de A e B
    const X = A + B;

    // Imprimir o resultado
    console.log('A soma de A e B é: ' + X);

    // Fechar a interface de leitura
    rl.close();
  });
});
