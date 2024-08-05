document.addEventListener('DOMContentLoaded', () => {
    require(['vs/editor/editor.main'], function () {
        const editor = monaco.editor.create(document.getElementById('editor'), {
            value: '',
            language: 'cpp',
            theme: 'vs-dark',
            automaticLayout: true
        });
        let notificationsShown = false;
        let lastClick = '';
        async function fetchAndSetValue(url) {
            try {
                const response = await fetch(url);
                if (!response.ok) {
                    throw new Error(`Failed to fetch ${url}`);
                }
                const code = await response.text();
                editor.setValue(code);
            } catch (error) {
                console.error(error);
            }
        }
        document.getElementById('btnCanvas').addEventListener('click', () => {
            window.electron.ipcRenderer.send('show-canvas');
            document.getElementById('canvasWindow').style.display = 'block';
            document.getElementById('textEditorWindow').style.display = 'none';
        });

        document.getElementById('btnTextEditor').addEventListener('click', () => {
            window.electron.ipcRenderer.send('show-text-editor');
            document.getElementById('canvasWindow').style.display = 'none';
            document.getElementById('textEditorWindow').style.display = 'block';
        });
        fetchAndSetValue('../_tests/_tests/_test_files/basic_test.cpp');

        document.getElementById('btnBasicTest').addEventListener('click', () => {
            lastClick = "btnBasicTest";
            fetchAndSetValue('../_tests/_tests/_test_files/basic_test.cpp');
        });

        document.getElementById('btnTestB').addEventListener('click', () => {
            lastClick = "btnTestB";
            fetchAndSetValue('../_tests/_tests/_test_files/testB.cpp');
        });

        document.getElementById('btnStudentFile').addEventListener('click', () => {
            lastClick = "btnStudentFile";
            fetchAndSetValue('../_tests/includes/array_functions/student.cpp');
           
        });

        document.getElementById('saveTestB').addEventListener('click', async () => {
            if (lastClick === 'btnTestB') {
                const code = editor.getValue();
                window.electron.ipcRenderer.send('save-test-B', code);
                const message = await new Promise(resolve => {
                    window.electron.ipcRenderer.once('save-testB-reply', (event, message) => resolve(message));
                });
                if (message === 'success') {
                    console.log('TestB code saved successfully');
                } else {
                    console.error('Failed to save TestB code');
                }
            } else {
                alert('Please click testB.cpp before saving cpp file.');
            }
        });

        document.getElementById('saveStudentFile').addEventListener('click', async () => {
            if (lastClick === 'btnStudentFile') {
                const code = editor.getValue();
                window.electron.ipcRenderer.send('save-student-file', code);
                const message = await new Promise(resolve => {
                    window.electron.ipcRenderer.once('save-student-file-reply', (event, message) => resolve(message));
                });
                if (message === 'success') {
                    console.log('The student\'s code was saved successfully');
                } else {
                    console.error('Failed to save the student\'s code');
                }
            } else {
                alert('Please click your cpp file before saving.');
            }
        });

        document.getElementById('runBasicTest').addEventListener('click', async () => {
            const output = await window.electron.compileCpp("basic_test");
            document.getElementById('codeOutput').innerText = output;
        });

        document.getElementById('runTestB').addEventListener('click', async () => {
            const output = await window.electron.compileCpp("testB");
            document.getElementById('codeOutput').innerText = output;
        });

        document.getElementById('submitExam').addEventListener('click', async () => {
            const output = await window.electron.compileCpp("testB");
            await window.electron.sendEmail(output);
        });

        document.getElementById('exitBtn').addEventListener('click', () => {
            notificationsShown = true;
            const confirmExit = window.confirm('Are you sure you want to exit the Exam?');
            if (confirmExit) {
                window.electron.ipcRenderer.send('exit-app');
            }
        });

        let counterElement = document.getElementById('counter');
        let modal = document.getElementById('myModal');
        let off_screen_counter = 0;
        let offScreen = document.getElementById('numberOftabs');

        window.electron.ipcRenderer.on('close-window', () => {
            notificationsShown = true;
            const confirmExit = window.confirm('Are you sure you want to exit the Exam?');
            if (confirmExit) {
                window.electron.ipcRenderer.send('exit-app');
            }
        });

        window.electron.ipcRenderer.on('blur-app', () => {
            if (!notificationsShown) {
                startTimer();
                notificationsShown = true;
                off_screen_counter++;
                modal.style.display = "block";
                updateCounter();
            }
        });

        function updateCounter() {
            let minutes = Math.floor(time_counter / 60);
            let seconds = time_counter % 60;
            counterElement.textContent = `${padTime(minutes)}:${padTime(seconds)}`;
            offScreen.textContent = off_screen_counter;
            setTimeout(() => {
                updateCounter();
            }, 1000);
            displayCheater();
        }

        window.electron.ipcRenderer.on('focus-app', () => {
            stopTimer();
            notificationsShown = false;
            modal.style.display = "none";
        });
    });
});
