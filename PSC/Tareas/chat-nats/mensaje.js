class Mensaje {
    fecha;
    constructor(msg, autor) {
        this.msg = msg;
        this.autor = autor;
        this.fecha = Date.now()
    }
}

export default Mensaje;