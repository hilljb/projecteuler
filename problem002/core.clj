(ns project-euler-002.core
  (:gen-class))


(defn fibonacci_seq
  "Creates a lazy Fibonacci sequence."
  ; If called without arguments, initiate the sequence with a=1 and b=1.
  ([] (fibonacci_seq 1 1))
  ; If called with arguments, cons 'a' with a recursive call using 'b' and 'a+b'.
  ([a b] (cons a (lazy-seq (fibonacci_seq b (+ a b))))))


(defn -main
  "Solves Project Euler problem 2 and returns the solution."
  [& args]
  (def fib (fibonacci_seq))
  (println (time
            (apply + (filter even? (take-while #(<= % 4000000) fib))))))
