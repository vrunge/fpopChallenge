# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

fpopChallenge <- function(vectData, penalty) {
    .Call(`_fpopChallenge_fpopChallenge`, vectData, penalty)
}

fpopRunge <- function(vectData, penalty, algoType = 1L) {
    .Call(`_fpopChallenge_fpopRunge`, vectData, penalty, algoType)
}

fpopRomano <- function(vectData, penalty) {
    .Call(`_fpopChallenge_fpopRomano`, vectData, penalty)
}

