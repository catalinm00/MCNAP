import { Publisher } from "zeromq";

class Chat {
    
    sockPub = new Publisher();

    constructor() { }

    async conectar() {
        await this.sockPub.bind("tcp://127.0.0.1:8001");
    }

    async enviarMensaje(msg) {
        await this.#recibirMensaje(msg);
    }

    async #recibirMensaje(msg) {
        await this.sockPub.send(msg);
    }

    desconectar() {
        this.sockPub.close();
    }
}

export default Chat;