{-  
-- EPITECH PROJECT, 2023
-- wolfram.hs
-- File description:
-- print beautiful stuff
-}

module Main (main) where

import System.Environment
import System.Exit
import Text.Read
import Control.Monad (when)
import Control.Monad (unless)

inputs :: String -> [Maybe Int] -> Int -> [Maybe Int]
inputs x xs index = take 5 $ send_args index (readMaybe x) xs

send_args :: Int -> a -> [a] -> [a]
send_args n newValue xs = take n xs ++ [newValue] ++ drop (n+1) xs

error_handling :: [String] -> [Maybe Int] -> IO [Maybe Int]
error_handling [] output = return output
error_handling ("--rule":x:xs) output = error_handling xs (inputs x output 0)
error_handling ("--start":x:xs) output = error_handling xs (inputs x output 1)
error_handling ("--lines":x:xs) output = error_handling xs (inputs x output 2)
error_handling ("--window":x:xs) output = error_handling xs (inputs x output 3)
error_handling ("--move":x:xs) output = error_handling xs (inputs x output 4)
error_handling _ output = return (replicate 5 Nothing)

rule30 :: [Char] -> Char
rule30 xs
    | xs `elem` ["*  ", " **", " * ", "  *"] = '*'
    | otherwise = ' '

rule90 :: [Char] -> Char
rule90 xs
    | xs `elem` ["** ", "*  ", " **", "  *"] = '*'
    | otherwise = ' '

rule110 :: [Char] -> Char
rule110 xs
    | xs `elem` ["** ", "* *", " **", " * ", "  *"] = '*'
    | otherwise = ' '

link_rules :: Int -> [Char] -> Char
link_rules 30 xs = rule30 xs
link_rules 90 xs = rule90 xs
link_rules 110 xs = rule110 xs 
link_rules _ _ = ' '

set_array :: [Char] -> [Char] -> Int -> [Char]
set_array lastLine output rule
    | length tmp /= 3 = output
    | otherwise = set_array (tail lastLine) (link_rules rule tmp : output) rule
    where
        tmp = take 3 lastLine

get_inputs :: [Maybe Int] -> [Int] -> Int -> IO [Int]
get_inputs xs output 5 = return $ reverse output ++ replicate 5 (-84)
get_inputs xs output index = get_inputs xs (handleValue index n : output) (index + 1)
  where
    n = maybe (-84) id (xs !! index)
    handleValue 0 n | n `elem` [30, 90, 110] = n
    handleValue 1 n | n >= 0 = n
    handleValue 3 n | n >= 0 = n
    handleValue 2 (-100) = -1
    handleValue _ n = n

mainLoop :: [Int] -> Int -> String -> Int -> IO ()
mainLoop xs 0 _ _ = return ()
mainLoop xs count lastLine gene
  | gene > 0 = mainLoop xs count updatedLastLine (gene - 1)
  | otherwise = render_array lastLine (xs !! 3) (xs !! 4)
              >> mainLoop xs (count - 1) updatedLastLine gene
  where
    updatedLastLine =
        let paddedLine = "  " ++ lastLine ++ "  "
            updatedArray = set_array paddedLine [] (xs !! 0)
      in reverse updatedArray

main :: IO ()
main = do
  args <- getArgs
  let numArgs = length args
      defaults = [-84, 0, -100, 80, 0]
  tmp <- error_handling args $
    zipWith (\x def -> maybe (Just def) Just (readMaybe x))
      (repeat "") defaults
  inputs_values <- get_inputs tmp [] 0
  let invalidInputs = any (== -84) inputs_values
  unless (numArgs > 0 && even numArgs && not invalidInputs) $
    exit "Error, verify your arguments" False
  let (arg1:arg2:arg3:_) = inputs_values
  mainLoop inputs_values arg3 "*" arg2
  return ()


exit :: String -> Bool -> IO ()
exit x False = putStrLn x >> exitFailure
exit _ True = exitSuccess

grep :: String -> String -> [String]
grep = undefined

begin_setter :: Int -> Int -> Int -> Int
begin_setter win seg move = index
  where
    halfWin = div win 2
    halfSeg = div seg 2
    index = if even seg && odd win
              then halfWin - halfSeg + 1 + move
              else halfWin - halfSeg + move

set_tab :: Int -> [Char] -> [Char]
set_tab count output = replicate count ' ' ++ output

overlap :: Int -> [Char] -> [Char] -> [Char] -> Int -> Int -> Int -> [Char]
overlap size ini output line actual_line new_line overline
    | size <= actual_line = output
    | actual_line >= new_line && actual_line < overline && length line /= 0 =
        overlap size (tail ini) ((head line) : output) (tail line)
            (actual_line + 1) new_line overline
    | length ini /= 0 =
        overlap size (tail ini) ((head ini) : output) line
            (actual_line + 1) new_line overline
    | otherwise = output

make_a_jump :: Int -> [Char] -> [Char] -> [Char] -> Int -> Int -> Int -> [Char]
make_a_jump size ini output line actual_line new_line overline
  | size <= actual_line = output
  | actual_line < overline && not (null line) =
      overlap size (tail ini) (head line : output) (tail line)
        (actual_line + 1) new_line overline
  | not (null ini) =
      overlap size (tail ini) (head ini : output) line
        (actual_line + 1) new_line overline
  | otherwise = output
    
count_line :: String -> Int -> String
count_line str n
  | (n + 1 >= 1 || length str <= 0) = str
  | otherwise                       = count_line (tail str) (n + 1)

render_array :: String -> Int -> Int -> IO ()
render_array str win move = putStrLn $ case started of
  n | n < 1 -> reverse $ make_a_jump win (set_tab win []) [] trimmedStr 0 n end
  n | n < win -> reverse $ overlap win (set_tab win []) [] trimmedStr 0 n end
  _ -> set_tab win []
  where
    started = begin_setter win (length str) move
    trimmedStr = count_line str started
    end = started + length str