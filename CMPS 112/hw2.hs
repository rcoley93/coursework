-- Ryan Coley
-- hw2.hs

-- 1
myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl f x [] = x
myFoldl f x (y:ys) = myFoldl f (f x y) ys

-- 2
myReverse :: [a] -> [a]
myReverse [] = []
myReverse (x:xs) = (myReverse xs) ++ [x]

-- 3
myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr f x y = foldl g id y x where g = (\h a b -> h (f a b))

-- 4
myFoldl2 :: (a -> b -> a) -> a -> [b] -> a
myFoldl2 f x y = foldr g id y x where g = (\h a b -> a (f b h))

-- 5
isUpper :: Char -> Bool
isUpper x = elem x ['A'..'Z']

-- 6
onlyCapitals1 :: String -> String
onlyCapitals1 x = filter isUpper x

-- 7 
onlyCapitals2 :: String -> String
onlyCapitals2 x = [c | c <- x, isUpper c]

-- 8
onlyCapitals3 :: String -> String
onlyCapitals3 [] = []
onlyCapitals3 (x:xs) | isUpper x = x:onlyCapitals3 xs 
                     | otherwise = onlyCapitals3 xs

-- 9
divRemainder :: Int -> Int -> (Int, Int)
divRemainder x y = (div x y, mod x y)

-- 10
digitSum :: Int -> Int
digitSum x | x == 0 = 0
           | otherwise = (mod x 10) + digitSum (div x 10)

-- 11
sayNum :: Integer -> String
sayNum x | x > (10^66 - 1) = error "Input accepts [0,10^66)"
         | x < 0 = error "Input accepts [0,10^66)"
         |otherwise = unwords (getMultipliers ((length groups) - 1) (map getNumWord groups)) where groups = getDigits x

--gets all the digits from a number in groups of 3
getDigits :: Integer -> [Int]
getDigits x | x == 0 = []
            | otherwise = getDigits(div x 1000) ++ [fromIntegral (mod x 1000) :: Int]

--gets the word associated with the number
getNumWord :: Int -> String
getNumWord x | x == 0 = upTo19!!0
             | x < 20 = upTo19!!x
             | x < 100 = if (mod x 10) == 0 then twentyTo90!!(div x 10) else twentyTo90!!(div x 10)++" "++getNumWord(mod x 10)
             | otherwise = if (mod x 100) == 0 then upTo19!!(div x 100)++" "++multitpliers!!0 else upTo19!!(div x 100)++" "++multitpliers!!0++" "++getNumWord(mod x 100)

--gets the multiplier associated with the group
getMultipliers :: Int -> [String] -> [String]
getMultipliers 0 x = x
getMultipliers p (x:xs) = x:(multitpliers!!p):(getMultipliers (p-1) xs)

--list of names of numbers
--0 - 19
upTo19 = ["zero","one","two","three","four","five","six","seven","eight","nine","ten",
        "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"]
twentyTo90 = ["","","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninety"]
multitpliers = ["hundred","thousand","million","billion","trillion","quadrillion","quintillion","sextillion",
                "septillion","octillion","nonillion","decillion","undecillion","duodecillion","tredecillion",
                "quattuordecillion","quindecillion","sexdecillion","septendecillion","octodecillion","novemdecillion",
                "vigintillion"]