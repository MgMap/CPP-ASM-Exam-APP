//const {compileCpp} = require('./compile')
const { ipcRenderer, dialog } = require('electron');

const btnCanvas = document.getElementById("btnCanvas");
const btnTextEditor = document.getElementById("btnTextEditor");



btnCanvas.addEventListener('click', () => {
    
    // Send an IPC message to the main process to display the Canvas window
    ipcRenderer.send('show-canvas');
});

btnTextEditor.addEventListener('click', () => {
    // Send an IPC message to the main process to display the Text Editor window
  
    ipcRenderer.send('show-text-editor');
    console.log("send show text editor");
});

// Handle IPC messages from the main process
ipcRenderer.on('show-canvas', (event, arg) => {
    // Show the Canvas window and hide the Text Editor window

    // document.getElementById("canvasWindow").style.display = "block";
    // document.getElementById("textEditorWindow").style.display = "none";
    console.log('Canvas view shown');
});

ipcRenderer.on('show-text-editor', () => {
    // Show the Text Editor window and hide the Canvas window
    //document.getElementById("canvasWindow").style.display = "none";
    document.getElementById("textEditorWindow").style.display = "block";
    console.log('Text Editor view shown');
});


const exitBtn = document.getElementById('exitBtn');

exitBtn.addEventListener('click', () => {
    // Send a message to the main process to request application closure
    const confirmExit = window.confirm('Are you sure you want to exit the Exam?');

    if(confirmExit)
    {
        ipcRenderer.send('exit-app');
    }
});

ipcRenderer.on('close-window', () => {
    const confirmExit = window.confirm('Are you sure you want to exit the Exam?');

    if(confirmExit)
    {
    ipcRenderer.send('exit-app');
    }
});





/*
// Call the initializeEditor function when the DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    initializeEditor();
  });*/

