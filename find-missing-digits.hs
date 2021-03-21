import Data.Char (digitToInt)

findCodeWith originalDigit = filter (\x -> verifyDigit x == originalDigit) . replaceMissing

verifyDigit = isDigitZero . flip rem 11 . sum . zipWith (*) (cycle [2..9]) . map digitToInt . reverse
  where
    isDigitZero 0 = 0
    isDigitZero 1 = 0
    isDigitZero n = 11 - n

replaceMissing num = go num ""
  where
    go [] acc = pure (reverse acc)
    go (x:xs) acc | x == 'x'  = do n <- "0123456789"
                                   go xs (n:acc)
                  | otherwise = go xs (x:acc)


main = print $ findCodeWith 3 "123x5678910x11213"
