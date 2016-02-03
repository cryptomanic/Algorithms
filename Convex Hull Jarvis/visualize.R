library(ggplot2)

# extract all points
f1 <- read.csv("allpoints.txt", 
               col.names = c("xcoor", "ycoor"), 
               sep = " ")

# points on the boundaries
f2 <- read.csv("selectedpoints.txt", 
               col.names = c("xcoor", "ycoor"), 
               sep = " ")

# plot all points 
plot1 <- ggplot(f1,  mapping = aes(xcoor, ycoor))
plot2 <- plot1 + geom_point(col = "red", size = 5)
total <- nrow(f2)

# join segments for getting the convex hull
plot3 <- plot2 + geom_path(mapping = aes(xcoor, ycoor), data = f2,
                           col = "blue", size = 1.2)

plot3 + geom_segment(aes(x = f2$xcoor[1], y = f2$ycoor[1], 
                         xend = f2$xcoor[total], yend = f2$ycoor[total]), 
                         col = "blue", size = 1.2)