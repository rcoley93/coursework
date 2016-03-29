--Ryan Coley
--hw1.hs

-- 1
citeAuthor :: String -> String -> String
citeAuthor x y = y ++ ", " ++ x

-- 2
initials :: String -> String -> String
initials x y = (x!!0):"."++(y!!0):"."

-- 3
title :: (String, String, Int) -> String
title (_,x,_) = x

-- 4
citeBook :: (String, String, Int) -> String
citeBook (x,y,z) = y ++ " (" ++ x ++ ", " ++ show z ++ ")"

-- 5
bibliography_rec :: [(String, String, Int)] -> String
bibliography_rec [] = ""
bibliography_rec (x:xs) = citeBook x ++ "\n" ++ bibliography_rec xs

-- 6
--returns the year from a tuple
getYear :: (String, String, Int) -> Int
getYear (a,b,c) = c

averageYear :: [(String, String, Int)] -> Int
averageYear x = div (sum (map (getYear) x)) (length x)

-- 7
--remove everything except for numbers
removeLetters :: String -> String
removeLetters x = [ c | c <- x, elem c ['1'..'9']]
--determine if word is a reference
isReference :: String -> Bool   
isReference x = if (head x) == '[' && (last x) == ']' && (length (removeLetters x)) > 0 then True else False

references :: String -> Int
references x = length (filter (isReference) (words x))

-- 8
--returns a reference
getReference :: String -> [(String,String,Int)] -> String
getReference w c = citeBook(c!!((read (removeLetters w) :: Int)-1))

--goes through the words and replaces references with citations
citeTextRecursive :: [String] -> [(String,String,Int)] -> [String]
citeTextRecursive [] c = [];
citeTextRecursive (t:ts) c = if (isReference t) then (getReference t c):(citeTextRecursive ts c) else t:(citeTextRecursive ts c)

citeText :: [(String, String, Int)] -> String -> String
citeText c t = unwords( citeTextRecursive (words t) c)

--test data
booklist :: [(String,String,Int)]
booklist = [("TFIOS","JOHN GREEN",2007),("WILL GREYSON, WILL GREYSON","JOHN GREEN",2010),("PAPER TOWNS","JOHN GREEN",2009)]
txt :: String
txt = "[1] and [2] both feature characters who will do whatever it takes to " ++
      "get to their goal, and in the end the thing they want the most ends " ++
      "up destroying them.  In case of [2] this is a whale..."
gatsby :: (String,String,Int)
gatsby =("F. Scott Fitzgerald", "Great Gatsby", 1925)
moby :: (String,String,Int)
moby = ("Herman Melville", "Moby Dick", 1851)