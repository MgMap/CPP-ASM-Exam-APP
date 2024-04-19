const {compileCpp} = require('./compile')
const { ipcRenderer } = require('electron');

const btnCanvas = document.getElementById("btnCanvas");
const btnTextEditor = document.getElementById("btnTextEditor");

btnCanvas.addEventListener('click', () => {
    
    // Send an IPC message to the main process to display the Canvas window
    ipcRenderer.send('show-canvas');
});

btnTextEditor.addEventListener('click', () => {
    // Send an IPC message to the main process to display the Text Editor window
    ipcRenderer.send('show-text-editor');
});

// Handle IPC messages from the main process
ipcRenderer.on('show-canvas', (event, arg) => {
    // Show the Canvas window and hide the Text Editor window
    
    console.log("render receives show-canvas")
    console.log("the argument is", arg)

    //document.getElementById("canvasWindow").style.display = "block";
    //document.getElementById("textEditorWindow").style.display = "none";
});

ipcRenderer.on('show-text-editor', () => {
    // Show the Text Editor window and hide the Canvas window
    document.getElementById("canvasWindow").style.display = "none";
    document.getElementById("textEditorWindow").style.display = "block";
});

let editor = document.querySelector("#editor");

editor = ace.edit(editor, {
  theme: "ace/theme/cobalt",
  mode: "ace/mode/c_cpp",
});

document.addEventListener('DOMContentLoaded', async ()=>{
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../includes/poly/poly.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch poly.cpp');
        }
        const polyCode = await response.text();

        //console.log(basicTestCppCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(polyCode);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
})

const btnBasicTest = document.getElementById("btnBasicTest")
btnBasicTest.addEventListener('click', async () => {
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../_tests/_test_files/basic_test.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch basic_test.cpp');
        }
        const basicTestCppCode = await response.text();

        //console.log(basicTestCppCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(basicTestCppCode);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
});

const btnTestB = document.getElementById("btnTestB")
btnTestB.addEventListener('click', async () => {
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../_tests/_test_files/testB.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch testB.cpp');
        }
        const testBCode = await response.text();

        //console.log(testBCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(testBCode);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
});

const btnPoly = document.getElementById("btnPoly")
btnPoly.addEventListener('click', async () => {
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../includes/poly/poly.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch poly.cpp');
        }
        const testBCode = await response.text();

        //console.log(testBCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(testBCode);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
});

const submitBtn = document.getElementById("submitBtn")
submitBtn.addEventListener('click', () => {

    // Get the code from the textarea
    const code = editor.getValue();
    console.log("code is", code);
    // Only proceed if there is code to compile and run
    if (code.trim() !== '') {
        compileCpp(code, "main");
    } else {
        alert('Please enter some code before submitting.');
    }
});


const runBasicTest = document.getElementById("runBasicTest")
runBasicTest.addEventListener('click', () => {

    // Get the code from the textarea
    const code = editor.getValue();
    console.log("code is", code);
    // Only proceed if there is code to compile and run
    if (code.trim() !== '') {
        compileCpp(code, "basic_test");
    } else {
        alert('Please enter some code before submitting.');
    }
});

const runTestB = document.getElementById("runTestB")
runTestB.addEventListener('click', () => {

    // Get the code from the textarea
    const code = editor.getValue();
    console.log("code is", code);
    // Only proceed if there is code to compile and run
    if (code.trim() !== '') {
        compileCpp(code, "testB");
    } else {
        alert('Please enter some code before submitting.');
    }
});

const exitBtn = document.getElementById('exitBtn');

exitBtn.addEventListener('click', () => {
    // Send a message to the main process to request application closure
    ipcRenderer.send('exit-app');
});



/*
// Call the initializeEditor function when the DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    initializeEditor();
  });*/

