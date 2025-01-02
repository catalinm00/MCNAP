import * as nats from 'nats'

class Chat {
    
    natsClient;

    constructor() { }

    async conectar() {
        this.natsClient = await nats.connect({servers: ["tcp://127.0.0.1:4222"]});
    }

    async enviarMensaje(msg) {
        await this.#recibirMensaje(msg);
    }

    async #recibirMensaje(msg) {
        await this.natsClient.publish("client.receive", msg);
    }

    async desconectar() {
        await this.natsClient.close();
    }
}

export default Chat;