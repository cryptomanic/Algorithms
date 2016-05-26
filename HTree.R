# code to generate HTree


gg <- ggplot() + xlim(-8, 8) + ylim(-10, 10)

constructHTree <- function(x, y, length, depth, gg) {
  if(depth != 0) {
    x0 <- x - length/2
    x1 <- x + length/2
    
    y0 <- y - (length/sqrt(2))/2
    y1 <- y + (length/sqrt(2))/2
    
    gg <- gg + geom_line(aes(x, y), data.frame(x = c(x0, x1), 
                                               y = c(y, y)))
    gg <- gg + geom_line(aes(x, y), data.frame(x = c(x0, x0), 
                                               y = c(y0, y1)))
    gg <- gg + geom_line(aes(x, y), data.frame(x = c(x1, x1), 
                                               y = c(y0, y1)))
    
    gg <- constructHTree( x0,y0 , length/2, depth-1, gg)
    gg <- constructHTree( x0,y1 , length/2, depth-1, gg)
    gg <- constructHTree( x1,y0 , length/2, depth-1, gg)
    gg <- constructHTree( x1,y1 , length/2, depth-1, gg)
  }
  return(gg)
}

constructHTree(0, 0, 8, 3, gg)
