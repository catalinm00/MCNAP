import os
import uuid
import shutil


def run(input, output, mapper, reducer, config={}):

    # job unique id
    uid = str(uuid.uuid4())

    print(f"[Job {uid}] Preparing new job with uid {uid} ...")

    # copy data to new folder
    os.makedirs(f"mapred/{uid}")
    shutil.copy(mapper, f"mapred/{uid}/mapper.py")
    shutil.copy(reducer, f"mapred/{uid}/reducer.py")
    shutil.copy("partition.py", f"mapred/{uid}/partition.py")
  
    # merge all inputs
    if os.path.isdir(input):
        files = os.listdir(input)  
        os.system("cat " + " ".join([f"{input}/{file}" for file in files]) + f" > mapred/{uid}/input")
    else: shutil.copy(input, f"mapred/{uid}/input")
        
    print(f"[Job {uid}] Prepared.")

    # Simulate MapReduce
    print(f"[Job {uid}] Executing MapReduce ...")
    os.system(f"cat mapred/{uid}/input | python3 mapred/{uid}/mapper.py | sort -t 1 | python3 mapred/{uid}/reducer.py > mapred/{uid}/output")
    print(f"[Job {uid}] Executed.")

    # Copy to output
    print(f"[Job {uid}] Copying output ...")
    shutil.copy(f"mapred/{uid}/output", output)
    print(f"[Job {uid}] Copied.")
