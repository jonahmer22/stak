# STAK

Stak is a stack based programming language that follows `FORTH` in principal but with some more modern niceties.

## Example Program

This is an example program using the `stak` language.

> *assuming everything goes to plan with deveopment

```
def fizzbuzz n {
  sum: 0

  for i in 1..n {
    if i 15 mod 0 = {
      "FizzBuzz " print
    } else if i 3 mod 0 = {
      "Fizz " print
      sum: sum i +
    } else if i 5 mod 0 = {
      "Buzz " print
    } else {
      i print
    }
  }

  "Sum of multiples of 3: " print
  sum print
}

20 fizzbuzz
```