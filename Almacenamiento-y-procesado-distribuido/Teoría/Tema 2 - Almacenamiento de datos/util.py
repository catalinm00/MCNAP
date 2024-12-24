def write(sock, text):
    print(f"write ({text})")
    data = text.encode()
    sock.sendall(len(data).to_bytes(2, 'big'))
    sock.sendall(data)

def read(sock):
    print("read()")
    bytes_to_read = int.from_bytes(sock.recv(2), 'big')
    chunks = []
    while bytes_to_read > 0:
        data = sock.recv(bytes_to_read)
        bytes_to_read -= len(data)
        chunks.append(data)
    return b"".join(chunks).decode()