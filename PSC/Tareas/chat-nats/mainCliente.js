import * as nats from 'nats'
import Cliente from './cliente.js'

const urlServidor = process.argv[2] ||  'tcp://localhost';
const usuario = process.argv[3] || 'user';

async function leer_de_teclado() {
    console.log("Escribe tu mensaje:");
    const stdin = process.openStdin();
    stdin.addListener("data", async (data) => {
        let result = await cliente.enviarMensaje(data.toString());
        if (result == false) console.log("Error enviando mensaje");
    });
}

// nos suscribimos a los mensajes que recibe el cliente y los mostramos por pantalla conforme vaya llegando
async function suscribirAColaDeMensajes(callback) {
    cliente.colaMensajes.on('msg', (msg) => callback(msg.toString()))
}

// funcion para formatear y mostrar mensaje por pantalla
function mostrarMensaje(msg) {
    const message = JSON.parse(msg);
    if (message.autor != usuario) {
        process.stdout.clearLine(0);
        process.stdout.cursorTo(0);
        const date = new Date(message.fecha);
        console.log(`>>> ${date.getHours()}:${date.getMinutes()} - ${message.autor}: ${message.msg}`);
    }
}


// creamos cliente
const cliente = new Cliente(urlServidor, usuario);
cliente.conectar();
suscribirAColaDeMensajes(mostrarMensaje);

const natsClient = await nats.connect({json: true, servers: [urlServidor + ":4222"]});
const sub = natsClient.subscribe("client.receive");
(async () => {
    for await (const msg of sub) {
        cliente.recibirMensaje(msg.data.toString());
    }
})();

//leemos de la entrada estandar
leer_de_teclado();

process.on('SIGINT', async () => {
    process.stdin.destroy();
    await natsClient.close();
    await cliente.desconectar();
    console.log('\nClosed');
})