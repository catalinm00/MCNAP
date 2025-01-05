import { Subscriber } from 'zeromq';
import Cliente from './cliente.js'

const urlServidor = process.argv[2];
const usuario = process.argv[3];

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

const sockSub = new Subscriber();
sockSub.connect(urlServidor + ":8001");
sockSub.subscribe("");

suscribirAColaDeMensajes(mostrarMensaje)

//leemos de la entrada estandar
leer_de_teclado();

// logica del proxy que se usa en el chat,
for await (const [msg] of sockSub) {
    cliente.recibirMensaje(msg);
}

process.on('SIGINT', function () {
    cliente.disconnect();
    sockSub.close()
    console.log('\nClosed')
})