

def dummy(x): return x

def split(x): return x.split()

def words(x): return len(x.split())

def word(x): return (x,1)

def sum(accum, x): return x if accum is None else accum + x

def acercamiento(x): 
    from datetime import datetime
    fields = x.split(",")
    if fields[2] == '"Acercamiento"':
        d = datetime.fromisoformat(fields[0][1:-1])
        key = str(d.day) + "/" + str(d.month) + "/" + str(d.year)
        return (key, 1)

def alejamiento(x): 
    from datetime import datetime
    fields = x.split(",")
    if fields[2] == '"Alejamiento"':
        d = datetime.fromisoformat(fields[0][1:-1])
        key = str(d.day) + "/" + str(d.month) + "/" + str(d.year)
        return (key, 1)