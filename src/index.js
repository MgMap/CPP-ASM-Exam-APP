const { app, BrowserWindow, BrowserView, ipcMain, dialog } = require('electron');
const path = require('path');
const fs = require('fs');

let mainWindow;
let canvasView;
let editorView;

if (require('electron-squirrel-startup')) {
  app.quit();
}

const createWindow = () => {
  mainWindow = new BrowserWindow({
    width: 1600,
    height: 1000,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      contextIsolation: false,
      nodeIntegration: true,
    },
  });

  mainWindow.loadFile(path.join(__dirname, 'index.html'));

  mainWindow.on('close', (event) => {
    event.preventDefault();
    dialog.showMessageBox(mainWindow, {
      type: 'warning',
      message: 'Are you sure you want to exit the exam?',
      buttons: ['Yes', 'No'],
      defaultId: 1,
      cancelId: 1,
    }).then((response) => {
      if (response.response === 0) {
        mainWindow.destroy();
      }
    });
  });

  mainWindow.on('blur', () => {
    mainWindow.webContents.send('blur-app');
  });

  mainWindow.on('focus', () => {
    mainWindow.webContents.send('focus-app');
  });

  // Initialize the views but don't add them yet
  canvasView = new BrowserView({
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      contextIsolation: false,
      nodeIntegration: true,
    },
  });
  canvasView.webContents.loadURL('https://canvas.pasadena.edu');

  editorView = new BrowserView({
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      contextIsolation: false,
      nodeIntegration: true,
    },
  });
  editorView.webContents.loadURL(path.join(__dirname, 'editor.html')).then(() => {
    console.log('Editor view loaded successfully.');
  }).catch((err) => {
    console.error('Failed to load editor view:', err);
  });

  ipcMain.on('show-canvas', () => {
    if (mainWindow.getBrowserView() === editorView) {
      mainWindow.removeBrowserView(editorView);
    }
    mainWindow.addBrowserView(canvasView);
    canvasView.setBounds({ x: 32, y: 215, width: 1000, height: 770 });
  });

  ipcMain.on('show-text-editor', () => {
    if (mainWindow.getBrowserView() === canvasView) {
      mainWindow.removeBrowserView(canvasView);
    }
    mainWindow.addBrowserView(editorView);
    editorView.setBounds({ x: 32, y: 215, width: 1000, height: 770 });
    console.log("text-editor-index");
    mainWindow.webContents.send('show-text-editor');
  });

  ipcMain.on("please", ()=>
  {
    console.log("from editor.html");
  });
  ipcMain.on('fetch-file', (event) => {
    const filePath = path.join(__dirname, '../_tests/_test_files/basic_test.cpp');
    fs.readFile(filePath, 'utf8', (err, data) => {
      if (err) {
        console.error('Failed to read file:', err);
        return;
      }
      editorView.webContents.send('fetch-file', data);
    });
  });

  ipcMain.on('compile-code', (event, code) => {
    console.log('Compiling code:', code);
    editorView.webContents.send('compile-result', 'Compilation successful!');
  });

  ipcMain.on('exit-app', () => {
    mainWindow.destroy();
  });

  mainWindow.webContents.openDevTools();
};

app.whenReady().then(() => {
  createWindow();
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});
