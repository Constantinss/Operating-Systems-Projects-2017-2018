# Keys

You are presented with a bunch of lines that look like this:

```
8239b961379a4f9f854fd19d82b56dc9 24
8239b961379a4f9f854fd19d82b56dc9 39
8239b961379a4f9f854fd19d82b56dc9 39
8239b961379a4f9f854fd19d82b56dc9 18
8239b961379a4f9f854fd19d82b56dc9 25
533cc20dc02647cb98c9cc534112e092 66
533cc20dc02647cb98c9cc534112e092 12
```

The general format is `{key} {value}`, where `{key}` is some string (a hex representation of uuid4, to be preciese) and `{value}` is a positive integer.

`{key}` and `{value}` are separated by exactly one interval.

## The task

In a language of your choice, implement a program, that reads those lines from the standard input (stdin) and outputs the top 3 keys, regarding the sum of their values.

For example, if we have the following input:


```
f 1
g 2
f 3
h 10
f 5
h 2
```

The output should be:

```
h: 12
f: 9
g: 2
```

Where the sum of the values of all lines, containing `h` is `12`, containing `f` is `9` and containing `g` is `2`.

If there are keys with equal summed values in top3, output all the keys with the same summed value, ordered alphabetically and separated by `, `.

For example, if we have the following input:

```
c 1
b 1
a 1
```

The output should be:

```
a, b, c: 1
```

**The output should end with a newline.**

## The tests

Alongside the task, add tests, that proove your solution is correct. This is entirely up to you.

