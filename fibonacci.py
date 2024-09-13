from functools import cache

@cache
def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    return fib(n-1) + fib(n-2)


def fast_fib(n):
    a, b = 0, 1
    for _ in range(n):
        a, b = b, a+b
    return a


def main():
    line = input()
    if line.isdigit():
        n = int(line)
        print(fib(n))
    else:
        print("Not an integer!, exiting...")


if __name__ == "__main__":
    main()