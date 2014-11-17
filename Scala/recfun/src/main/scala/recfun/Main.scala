package recfun
import common._

object Main {
  def main(args: Array[String]) {
    println("Pascal's Triangle")
    for (row <- 0 to 10) {
      for (col <- 0 to row)
        print(pascal(col, row) + " ")
      println()
    }
  }

  /**
   * Exercise 1
   */
  def pascal(c: Int, r: Int): Int = {
    if (c > 0 && c < r) {
      pascal(c - 1, r - 1) + pascal(c, r - 1)
    } else {
      1
    }
  }

  /**
   * Exercise 2
   */
  def balance(chars: List[Char]): Boolean = {
    def findMatch(chars: List[Char], stack: Int): Boolean = {
      if (chars.isEmpty) {
        false
      } else if (chars.head == ')' && stack > 0) {
        findMatch(chars.tail, stack - 1)
      } else if (chars.head == ')' && stack == 0) {
        balance(chars.tail)
      } else if (chars.head == '(') {
        findMatch(chars.tail, stack + 1)
      } else {
        findMatch(chars.tail, stack)
      }
    }
    if (chars.isEmpty) {
      true
    } else if (chars.head == ')') {
      false
    } else if (chars.head == '(') {
      findMatch(chars.tail, 0)
    } else {
      balance(chars.tail)
    }
  }

  /**
   * Exercise 3
   */
  def countChange(money: Int, coins: List[Int]): Int = {
    def traverse(remainder: Int, coins: List[Int]): Int = {
      if (remainder == 0) {
        1
      } else if (remainder < 0) {
        0
      } else if (coins.isEmpty && remainder >= 0) {
        0
      } else {
        traverse(remainder, coins.tail) + traverse(remainder - coins.head, coins)
      }
    }
    if (coins.isEmpty || money == 0) {
      0
    } else {
      traverse(money, coins)
    }
  }
}
