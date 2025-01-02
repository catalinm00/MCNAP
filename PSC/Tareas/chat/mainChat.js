import { Reply } from 'zeromq';
import Chat from './chat.js';

const sock = new Reply()
await sock.bind("tcp://127.0.0.1:8000")
console.log("Server listening...")

const chat = new Chat();
await chat.conectar();

for await (const [msg] of sock) {
    await chat.enviarMensaje(msg);
    await sock.send("true");
}

process.on('SIGINT', function () {
    sock.close();
    chat.desconectar();
    console.log('\nClosed');
})