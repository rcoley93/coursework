-- Ryan Coley
-- hw4.hs

-- Imports and Declarations
{-# LANGUAGE FlexibleInstances, OverlappingInstances, UndecidableInstances #-}

import System.Random
import Data.Int
import Control.Monad

-- 1

class (Show a) => Gen a where
  gen :: IO a

instance (Show a, Random a) => Gen a where
  gen = randomIO

instance (Gen a, Gen b) => Gen (a, b) where
  gen = do
         a <- gen
         b <- gen
         return (a,b)

instance (Gen a) => Gen [a] where
  gen = do
         listLength <- randomRIO (0, 10) :: IO Int
         list <- replicateM listLength gen
         return list
-- 2
class Testable t where
  test :: t -> IO (Bool,String)

instance Testable Bool where
  test b = return (b, show b)

instance (Gen input, Testable inputTest) => Testable (input -> inputTest) where
  test t = do
            x <- gen
            test (t x)

-- 3 & 4
quickCheck :: (Testable a) => Int -> a -> IO ()
quickCheck 0 _ = return ()
quickCheck n t = do
                  (b,s) <- test "" t
                  if b /= True then putStrLn $ "Failing Inputs " ++ s
                  else quickCheck (n-1) t

-- 5
testSort :: ([Int8] -> [Int8]) -> [Int8] -> Bool
testSort sort lst = let sorted = sort lst in
                        inOrder sorted
                        where inOrder (x:xs:xss) = x <= xs && inOrder (xs:xss)
                              inOrder _ = True
-- 6
isort :: [Int8] -> [Int8]
isort [] = []
isort (x:xs) = insert (isort xs) where
               insert [] = [x]
               insert (h:t) | x < h = x:h:t
                            | otherwise = h:(insert t)

qsort :: [Int8] -> [Int8]
qsort [] = []
qsort (x:xs) = qsort [a | a <- xs, a <= x] ++ [x] ++ qsort [a | a <- xs, a > x]
