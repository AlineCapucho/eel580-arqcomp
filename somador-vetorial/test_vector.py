import random

def binary_generator():
    binary = ""
 
    for i in range(32):
        binary += str(random.randint(0, 1))

    return(binary)

def adder(A_i, B_i, mode_i, vecSize_i):
    vec_size_map = {
        "00": 4,
        "01": 8,
        "10": 16,
        "11": 32
    }
    
    binary_size = 32
    vec_size = vec_size_map.get(vecSize_i)
    num_vecs = binary_size // vec_size

    S_o = ""

    for i in range(num_vecs):
        start = 32 - (i + 1) * vec_size
        end = 32 - i * vec_size
        
        A_vec = int(A_i[start:end], 2)
        B_vec = int(B_i[start:end], 2)
                
        if mode_i == "0":
            result = (A_vec + B_vec) & (1 << vec_size) - 1
        else:
            result = (A_vec - B_vec) & (1 << vec_size) - 1
        
        result = bin(result)[2:].zfill(vec_size)
        S_o = f"{result}{S_o}"

    return S_o

def main():
    vec_sizes = ["00", "01", "10", "11"]
    modes = ["0", "1"]

    with open("test_vector.txt", "w") as file:
        file.write("A_i[32] B_i[32] mode_i vecSize_i[2] S_o[32]\n")

        for size in vec_sizes:
            for mode in modes:
                for i in range(10):
                    A_i = binary_generator()
                    B_i = binary_generator()
                    S_o = adder(A_i, B_i, mode, size)

                    file.write(f"{A_i} {B_i} {mode} {size} {S_o}\n")

if __name__ == "__main__":
    main()