// Timer logic
let timerInterval;
let totalTimeInSeconds = 900; // Default exam time: 15 minutes
let secondsRemaining = totalTimeInSeconds;
let timerDisplay = document.getElementById('timer');
let examTimeInput = document.getElementById('examTime');
let startTimerBtn = document.getElementById('startTimerBtn');

startTimerBtn.addEventListener('click', startTimer);

function startTimer() {
  let examTime = parseInt(examTimeInput.value);
  if (examTime && examTime > 0) {
    totalTimeInSeconds = examTime * 60;
    secondsRemaining = totalTimeInSeconds;
    clearInterval(timerInterval);
    timerInterval = setInterval(updateTimerDisplay, 1000);
    updateTimerDisplay();
  } else {
    alert('Please enter a valid exam time.');
  }
}

function updateTimerDisplay() {
  let minutes = Math.floor(secondsRemaining / 60);
  let seconds = secondsRemaining % 60;
  timerDisplay.textContent = `${padTime(minutes)}:${padTime(seconds)}`;
  if (secondsRemaining === 0) {
    clearInterval(timerInterval);
    alert('Time\'s up! Please submit your exam.');
  }
  secondsRemaining--;
}

function padTime(time) {
  return time < 10 ? `0${time}` : time;
}
