import * as nats from 'nats'
import Chat from './chat.js';

const natsClient = await nats.connect({json: true, servers: ['tcp://localhost:4222']})
console.log("Server listening...")

const chat = new Chat();
await chat.conectar();

const sub = natsClient.subscribe("chat.send");
(async () => {
    for await (const msg of sub) {
        await chat.enviarMensaje(msg.data);
        msg.respond("true");
    }
})();

process.on('SIGINT', async () => {
    await natsClient.close()
    await chat.desconectar();
    console.log('\nClosed');
})