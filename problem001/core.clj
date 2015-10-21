(ns project-euler-001.core
  (:gen-class))


(defn f
  "Takes an input x. If 3 or 5 divides x, returns x. Otherwise, returns 0."
  [x]
  (if (or (= (mod x 3) 0) (= (mod x 5) 0)) x 0))


(defn -main
  "Project Euler Problem 1 - Clojure Solution"
  [& args]
  (println (time (reduce + (map f (range 1 1000))))))
