const array = [0, 1, 2, 3, 4, 5];

const alunos = [
    "Demetrius",
    "Marcos",
    "Vitor",
    "Guilherme",
    "Anderson",
    "Michela",
    "André"
];
let contador = 0;
for(let i = 0;i<array.length;i++){
    if(alunos[i].startsWith("M")){
        console.log(alunos[i]," index: ",i)
        contador++;
    }
}
console.log(contador)