const display = document.getElementById("display");
const buttons = document.querySelectorAll(".btn");
const clearButton = document.getElementById("clear");
const equalsButton = document.getElementById("equals");

let currentInput = ""; // Armazena o número ou operação em curso

// Adicionar eventos para os botões numéricos e operadores
buttons.forEach((button) => {
  button.addEventListener("click", () => {
    currentInput += button.textContent; // Concatena os valores clicados
    display.value = currentInput; // Exibe no display
  });
});

// Botão de limpar (C)
clearButton.addEventListener("click", () => {
  currentInput = ""; // Reseta o valor atual
  display.value = ""; // Limpa o display
});

// Botão de igual (=)
equalsButton.addEventListener("click", () => {
  try {
    // Calcula a expressão
    const result = eval(currentInput);
    display.value = result; // Mostra o resultado
    currentInput = result.toString(); // Atualiza o input para continuar cálculos
  } catch {
    // Caso a expressão seja inválida
    display.value = "Erro";
    currentInput = ""; // Reseta para evitar problemas futuros
  }
});
