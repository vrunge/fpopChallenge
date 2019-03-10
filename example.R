library(fpopChallenge)
y = c(rnorm(1e5, 3),
      rnorm(1e5, 0),
      rnorm(1e5, 5))
      
beta = 2 * length(y)
fpopRunge(vectData = y, vectWeight = 3, penalty = beta)
fpopRomano(vectData = y, penalty = beta)
