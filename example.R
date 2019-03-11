library(fpopChallenge)
y = c(rnorm(1e5, 3),
      rnorm(1e5, 0),
      rnorm(1e5, 5))
      

y <- c(rep(0, 10),
       rep(1, 10),
       rep(0, 10))

beta = 2 * (log(length(y)))


fpopRunge(vectData = y, vectWeight = 1.0, penalty = beta)

fpopRomano(vectData = y, penalty = beta)

ggplot(data.frame(t = 1:length(y), y), aes(x = t, y = y)) +
  geom_point() +
  geom_vline(xintercept = res$cp + 1, color = 2) +
  geom_vline(xintercept = cpt, col = 3,  lty = 3)
