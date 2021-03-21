import Data.Char (digitToInt)

findCodeWithDigit originalDigit num guesses = filter (\x -> verifyDigit x == originalDigit)  (replaceMissing num guesses)

verifyDigit = isDigitZero . flip rem 11 . sum . zipWith (*) (cycle [2..9]) . map digitToInt . reverse
  where
    isDigitZero 0 = 0
    isDigitZero 1 = 0
    isDigitZero n = 11 - n

replaceMissing num guesses = go num guesses ""
  where
    go [] _  acc = pure (reverse acc)
    go xs [] acc = pure $ (reverse acc) ++ xs
    go (x:xs) (g:gs) acc | x == 'x'  = do n <- g
                                          go xs gs (n:acc)
                         | otherwise = go xs (g:gs) (x:acc)

main = print $ findCodeWithDigit 7 "35170860744463005078550000003741901xxx04399" ["68", "38", "68"]
