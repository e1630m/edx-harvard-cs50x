var can = document.getElementById("breakout");
var ctx = can.getContext("2d");
function resizeCanvas() {
  can.width = Math.floor(window.innerWidth * 0.8) > 1137 ? 1137 : Math.floor(window.innerWidth * 0.8);
  can.height = Math.floor(can.width / 16 * 9);
}
resizeCanvas();
var ballRadius = 10;
var x = can.width / 2;
var y = can.height - 60;
var dx = 5;
var dy = -5;
var dxMax = 10;
var pHeight = 15;
var pWidth = Math.floor(can.width / 11);
var paddleX = (can.width - pWidth) / 2;
var pHover = 20;
var pSpeed = 8;
var rgtPressed = false;
var lftPressed = false;
var brRows = 8, brCols = 13;
var brHeight = 20, brWidth = Math.floor(can.width / brCols) - 10;
var brColors = ["#CA5683", "#D44348", "#CA6432", "#D5AA06", "#41A340", "#363BD2", "#7C45DE", "#05C5C6"];
var brPadding = 4;
var brOffsetT = 30;
var brOffsetL = Math.floor(can.width * 0.04);
var score = 0;
var lives = 3;
var bricks = [];
for (let r = 0; r < brRows; r++) {
  bricks[r] = [];
  for (let c = 0; c < brCols; c++) {
    bricks[r][c] = { x: 0, y: 0, alive: 1 };
  }
}
document.addEventListener("keydown", keyDn, false);
document.addEventListener("keyup", keyUp, false);
document.addEventListener("mousemove", mouse, false);

function keyDn(e) {
  if (["Right", "ArrowRight"].includes(e.key)) {
    rgtPressed = true;
  } else if (["Left", "ArrowLeft"].includes(e.key)) {
    lftPressed = true;
  }
}

function keyUp(e) {
  if (["Right", "ArrowRight"].includes(e.key)) {
    rgtPressed = false;
  } else if (["Left", "ArrowLeft"].includes(e.key)) {
    lftPressed = false;
  }
}

function mouse(e) {
  let relativeX = e.clientX - can.offsetLeft;
  if (relativeX > 0 && relativeX < can.width) {
    paddleX = relativeX - pWidth / 2;
  }
}

function brCollision() {
  for (let r = 0; r < brRows; r++) {
    for (let c = 0; c < brCols; c++) {
      let b = bricks[r][c];
      if (b.alive) {
        if (x > b.x && x < b.x + brWidth && y > b.y && y < b.y + brHeight) {
          dy = -dy;
          b.alive = 0;
          score++;
          if (score == brCols * brRows) {
            alert("YOU WIN");
            document.location.reload();
          }
        }
      }
    }
  }
}

function drawBall() {
  ctx.beginPath();
  ctx.arc(x, y, ballRadius, 0, Math.PI * 2);
  ctx.fillStyle = "#FCFCFC";
  ctx.fill();
  ctx.closePath();
}

function drawPaddle() {
  if (paddleX + pWidth > can.width) {
    paddleX = can.width - pWidth;
  } else if (paddleX < 0) {
    paddleX = 0;
  }
  ctx.beginPath();
  ctx.rect(paddleX, can.height - pHeight - pHover, pWidth, pHeight);
  ctx.fillStyle = "#6A7072";
  ctx.fill();
  ctx.closePath();
}

function drawBricks() {
  for (let r = 0; r < brRows; r++) {
    for (let c = 0; c < brCols; c++) {
      if (bricks[r][c].alive) {
        var brickX = c * (brWidth + brPadding) + brOffsetL;
        var brickY = r * (brHeight + brPadding) + brOffsetT;
        bricks[r][c].x = brickX;
        bricks[r][c].y = brickY;
        ctx.beginPath();
        ctx.rect(brickX, brickY, brWidth, brHeight);
        ctx.fillStyle = brColors[r];
        ctx.fill();
        ctx.closePath();
      }
    }
  }
}

function drawScore() {
  ctx.font = "18px Helvetica";
  ctx.fillStyle = "#FFFFFF";
  ctx.fillText("Score: " + score, 8, 20);
}

function drawLives() {
  ctx.font = "18px Helvetica";
  ctx.fillStyle = "#FFFFFF";
  ctx.fillText("Lives: " + lives, can.width - 65, 20);
}

function draw() {
  ctx.clearRect(0, 0, can.width, can.height);
  drawBricks();
  drawBall();
  drawPaddle();
  drawScore();
  drawLives();
  brCollision();

  if (x + dx > can.width - ballRadius || x + dx < ballRadius) {
    dx = -dx;
  }
  if (y + dy < ballRadius) {
    dy = -dy;
  }
  else if (y + dy > can.height - ballRadius - pHover - pHeight) {
    if (x > paddleX && x < paddleX + pWidth) {
      let xMod = pSpeed * 0.1;
      dy = -dy;
      dx += (xMod * rgtPressed) - (xMod * lftPressed);
      dx = dx > dxMax ? dxMax : dx < -dxMax ? -dxMax : dx;
    } else {
      lives--;
      if (!lives) {
        alert("GAME OVER");
        document.location.reload();
      } else {
        x = can.width / 2;
        y = can.height - 60;
        dx = 5;
        dy = -5;
        paddleX = (can.width - pWidth) / 2;
      }
    }
  }

  if (rgtPressed && paddleX < can.width - pWidth) {
    paddleX += pSpeed;
  } else if (lftPressed && paddleX > 0) {
    paddleX -= pSpeed;
  }

  x += dx;
  y += dy;
  requestAnimationFrame(draw);
}

draw();
