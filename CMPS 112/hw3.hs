-- Ryan Coley
-- hw3.ml

-- Imports
import qualified Data.List as D

--Data Declarations
data BST k v = Empty | Node k v (BST k v) (BST k v)
data JSON = JStr String | JNum Double | JArr [JSON] | JObj [(String, JSON)]

--Class Declarations
class Json a where
  toJson :: a -> JSON
  fromJson :: JSON -> a

-- 1
val :: BST k v -> Maybe v
val Empty = Nothing
val (Node k v l r) = Just v

-- 2
size :: BST k v -> Int
size Empty = 0
size (Node k v l r ) = 1 + (size  l) + (size r)

-- 3
ins :: (Ord k) => k -> v -> BST k v -> BST k v
ins k v Empty = (Node k v Empty Empty)
ins k v (Node nk nv l r) = if k == nk then
                              (Node nk v l r)
                           else if k < nk then
                              (Node nk nv (ins k v l) r)
                           else
                              (Node nk nv l (ins k v r))

-- 4
instance (Show v) => Show (BST k v) where
  show Empty = ""
  show (Node k v left right) = "(" ++ show left ++ show v ++ show right ++ ")"

-- 5
instance Show JSON where
  show (JStr s) = show s
  show (JNum d) = show d
  show (JArr js) = "[" ++ (D.intercalate "," (map show js)) ++ "]"
  show (JObj obj)  = "{" ++ (D.intercalate "," (map (\(x,y) -> show x ++ ":" ++ show y) obj)) ++ "}"

-- 6
instance Json Double where
   toJson x = JNum x
   fromJson x = read (show x) :: Double
instance (Json a, Read a) => Json [a] where
   toJson x = JArr (map toJson x)
   fromJson (JArr x) = map (\y -> read (show y)) x

--NOTES
-- data BST a = Leaf | Node a (BST a) (BST a) deriving (Show, Eq, Ord)

-- insert :: (Ord a) => a -> BST -> BST
-- insert n leaf = Node n leaf leaf
-- insert n (Node m l r) = if n < m then Node m (insert n l) r else Node m l (insert n r)

--showBST :: (Show a) => (BST a) -> String
--showBST leaf = "Leaf"
--showBST (Node n l r) = "(Node " ++ show n ++ (showBST l) ++ (showBST r) ++ ")"
--instance (Show a) => Show BST where show = showBST

-- eqBST :: (Eq a)=>(BST a) ->(BST a) -> Bool
-- instance (Eq a)=> Eq (BST a) where (==) = eqBST

--data Json = Jstr String | Jnum Double | Jarr [Json] | Jobj [(String, Json)]Json
--showJson :: Json -> String
--showJson (Jstr S) = S
--showJson (Jnum d) = show d
--showJson (Jarr js) = HW3
--showJson (Jobj kvs = HW3

--lunches :: [[(String, String)]]
--lunches = [[ ("day","Monday"),("loc","joes")]]
--toJson lunches
--lunchesToJson :: [[(String,String)]]
--lunchesToJson lunches = Jarr (map (\lunch -> Jobj (map (\(k,v)->(k,Jstr v)) lunch)) lunches)

--s2j :: S -> Json
--s2j = Jstr
--d2j :: D -> Json
--d2j == Jnum
--list2j::(a->Json)->[a]->Json
--list2j f = Jarr.(map f)


--class JSON a where toJson :: a -> Json
--instance JSON D where toJson = Jnum
--instance JSON String where toJson = Jstr
--instance (JSON a) => JSON [a] where toJson xs = Jarr (map toJson xs)
--instance (JSON a) => JSON [(String,a)] where toJson kvs = Jobj (map (\(k,v) -> (k,toJson v)) kvs)
--instance JSON json where toJson = id
--instance (JSON a, JSON b) => JSON (a,b) where toJson (a,b) = Jarr [toJson a,toJson b]

--let x = (1,2,...,9,0,1,...,6)
--x==x
