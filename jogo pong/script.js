const canvas = document.getElementById("pongCanvas");
const ctx = canvas.getContext("2d");

// Configurações do jogo
const paddleWidth = 100;
const paddleHeight = 10;
const ballRadius = 10;

let paddleX = (canvas.width - paddleWidth) / 2; // Posição inicial da barra
let ballX = canvas.width / 2; // Posição inicial da bola
let ballY = canvas.height - 30;
let ballSpeedX = 3; // Velocidade horizontal da bola
let ballSpeedY = -3; // Velocidade vertical da bola
let rightPressed = false;
let leftPressed = false;

// Eventos para controle do teclado
document.addEventListener("keydown", keyDownHandler);
document.addEventListener("keyup", keyUpHandler);

function keyDownHandler(e) {
  if (e.key === "ArrowRight") rightPressed = true;
  if (e.key === "ArrowLeft") leftPressed = true;
}

function keyUpHandler(e) {
  if (e.key === "ArrowRight") rightPressed = false;
  if (e.key === "ArrowLeft") leftPressed = false;
}

// Função para desenhar a bola
function drawBall() {
  ctx.beginPath();
  ctx.arc(ballX, ballY, ballRadius, 0, Math.PI * 2);
  ctx.fillStyle = "white";
  ctx.fill();
  ctx.closePath();
}

// Função para desenhar a barra
function drawPaddle() {
  ctx.beginPath();
  ctx.rect(paddleX, canvas.height - paddleHeight - 10, paddleWidth, paddleHeight);
  ctx.fillStyle = "white";
  ctx.fill();
  ctx.closePath();
}

// Função principal para desenhar o jogo
function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height); // Limpa o canvas
  drawBall();
  drawPaddle();

  // Atualiza a posição da bola
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Detecta colisão com as bordas laterais
  if (ballX + ballRadius > canvas.width || ballX - ballRadius < 0) {
    ballSpeedX = -ballSpeedX;
  }

  // Detecta colisão com a borda superior
  if (ballY - ballRadius < 0) {
    ballSpeedY = -ballSpeedY;
  }

  // Detecta colisão com a barra
  if (
    ballY + ballRadius > canvas.height - paddleHeight - 10 &&
    ballX > paddleX &&
    ballX < paddleX + paddleWidth
  ) {
    ballSpeedY = -ballSpeedY;
  }

  // Verifica se a bola toca a borda inferior (fim de jogo)
  if (ballY + ballRadius > canvas.height) {
    alert("Fim de jogo!");
    document.location.reload();
  }

  // Movimenta a barra
  if (rightPressed && paddleX < canvas.width - paddleWidth) {
    paddleX += 7;
  } else if (leftPressed && paddleX > 0) {
    paddleX -= 7;
  }

  requestAnimationFrame(draw); // Continua o loop do jogo
}

// Inicia o jogo
draw();
