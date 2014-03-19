Problem
=======

In England the currency is made up of pound, £, and pence, p, and there are eight coins in general
circulation:

    1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).

It is possible to make £2 in the following way:

    1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

How many different ways can £2 be made using any number of coins?

Details
=======

This is a very common functional/recursive programming exercise. It can be solved by creating a
function that iterates over quantities of a given coin and then calls itself to iterate over values
of another coin, and so on, until each possible result is determined. For each possible result,
return a 1 and have the recursive function calls sum those 1s to a total.

