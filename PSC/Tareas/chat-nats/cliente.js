import * as nats from 'nats'
import { EventEmitter } from 'node:events'
import Mensaje from './mensaje.js';

class Cliente {
    natsClient;
    colaMensajes = new EventEmitter();

    constructor(urlServidor, usuario) {
        this.urlServidor = urlServidor;
        this.usuario = usuario;
    }

    async conectar() {
        this.natsClient = await nats.connect({servers: [this.urlServidor + ":4222"]});
    }

    async enviarMensaje(texto) {
        const msg = new Mensaje(texto, this.usuario);
        const result = await this.natsClient.request("chat.send", JSON.stringify(msg))
        return result.data.toString() == "true";
    }

    async recibirMensaje(msg) {
        this.colaMensajes.emit("msg", msg)
    }

    async desconectar() {
        await this.natsClient.close();
    }
}

export default Cliente;