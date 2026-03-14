// ==========================================
// REVISÃO BÁSICA DE JAVASCRIPT
// ==========================================


// ------------------------------------------
// 1️⃣ VARIÁVEIS
// ------------------------------------------

// const → valor não muda
const nome = "Tamires";

// let → valor pode mudar
let idade = 22;

// JavaScript não usa int ou float
// todos os números são do tipo Number
let altura = 1.70;

console.log(nome);
console.log(idade);
console.log(altura);


// ------------------------------------------
// 2️⃣ IF / ELSE
// ------------------------------------------

let nota = 7;

if (nota >= 7) {
    console.log("Aprovado");
} else {
    console.log("Reprovado");
}


// ------------------------------------------
// 3️⃣ ARRAYS
// ------------------------------------------

// Array = lista de valores
let tarefas = ["estudar", "programar", "treinar"];

console.log(tarefas);

// acessar posição
console.log(tarefas[0]); // estudar

// adicionar item
tarefas.push("ler");

console.log(tarefas);


// ------------------------------------------
// 4️⃣ LOOP FOR
// ------------------------------------------

// percorre o array
for (let i = 0; i < tarefas.length; i++) {

    console.log("Tarefa:", tarefas[i]);

}


// ------------------------------------------
// 5️⃣ LOOP FOR OF
// ------------------------------------------

// forma mais moderna de percorrer array

for (let tarefa of tarefas) {

    console.log("Fazer:", tarefa);

}


// ------------------------------------------
// 6️⃣ FUNÇÕES
// ------------------------------------------

// função recebe valores e executa algo
function soma(a, b) {

    return a + b;

}

let resultado = soma(5, 3);

console.log("Resultado:", resultado);


// ------------------------------------------
// 7️⃣ OBJETOS
// ------------------------------------------

// objeto guarda dados estruturados

let pessoa = {

    nome: "Tamires",
    idade: 22,
    cidade: "Rio de Janeiro"

};

console.log(pessoa.nome);
console.log(pessoa.idade);


// ------------------------------------------
// 8️⃣ JSON
// ------------------------------------------

// JSON é formato de dados parecido com objeto

let usuarioJSON = `{
    "nome": "Tamires",
    "idade": 22
}`;

// converter JSON para objeto JS
let usuario = JSON.parse(usuarioJSON);

console.log(usuario.nome);


// ------------------------------------------
// 9️⃣ DOM - getElementById
// ------------------------------------------

// DOM permite manipular elementos HTML

// exemplo:
// <h1 id="titulo"></h1>

let titulo = document.getElementById("titulo");

// mudar texto do elemento
titulo.innerText = "Olá mundo";


// ------------------------------------------
// 🔟 EVENTOS
// ------------------------------------------

// exemplo HTML:
// <button id="botao">Clique</button>

let botao = document.getElementById("botao");

// quando clicar executa função
botao.addEventListener("click", function () {

    console.log("Botão clicado!");

});


// ------------------------------------------
// 11️⃣ ARRAY MAP (muito usado em React)
// ------------------------------------------

let numeros = [1, 2, 3, 4];

let dobrados = numeros.map(function (n) {

    return n * 2;

});

console.log(dobrados);


// ------------------------------------------
// 12️⃣ FILTER
// ------------------------------------------

let maiores = numeros.filter(function (n) {

    return n > 2;

});

console.log(maiores);