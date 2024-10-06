const { spawn } = require('child_process');
const path = require('path');

async function compileCpp(fileName) {
    const parentDir = path.resolve(__dirname, '..');
    let output = '';

    function clearOutput() {
        output = '';
    }

    function updateOutput(data) {
        output += data.toString();
    }

    function runCommand(command, args, cwd) {
        return new Promise((resolve, reject) => {
            const process = spawn(command, args, { cwd });

            process.stdout.on('data', (data) => {
                console.log(`${command} stdout: ${data}`);
                updateOutput(data);
            });

            process.stderr.on('data', (data) => {
                console.error(`${command} stderr: ${data}`);
                updateOutput(data);
            });

            process.on('close', (code) => {
                if (code === 0) {
                    resolve();
                } else {
                    reject(new Error(`${command} failed with code ${code}`));
                }
            });
        });
    }

    try {
        await runCommand('cmake', ['-S', '.', '-B', 'build'], parentDir);
        clearOutput();
        await runCommand('cmake', ['--build', path.resolve(parentDir, 'build')], parentDir);
        clearOutput();
        await runCommand(path.join(path.resolve(parentDir, 'build'), 'bin', fileName), [], parentDir);
        return output;
    } catch (error) {
        console.error(error);
        return output;
    }
}

module.exports = { compileCpp };
