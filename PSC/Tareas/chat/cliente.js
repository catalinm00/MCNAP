import { Request } from 'zeromq';
import { EventEmitter } from 'node:events'
import Mensaje from './mensaje.js';

class Cliente {
    sockRequest = new Request();
    colaMensajes = new EventEmitter();

    constructor(urlServidor, usuario) {
        this.urlServidor = urlServidor;
        this.usuario = usuario;
        this.sockRequest.connect(this.urlServidor + ":8000")

    }

    async enviarMensaje(texto) {
        const msg = new Mensaje(texto, this.usuario);
        await this.sockRequest.send(JSON.stringify(msg))
        const [result] = await this.sockRequest.receive()
        return result.toString() == "true";
    }

    async recibirMensaje(msg) {
        this.colaMensajes.emit("msg", msg)
    }

    disconnect() {
        this.sockRequest.disconnect();
    }
}

export default Cliente;