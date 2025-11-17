package main

import "github.com/gin-gonic/gin"

func main() {
	r := gin.Default()

	r.LoadHTMLFiles("../frontend/index.html")
	r.Static("/css", "../frontend/css")
	r.GET("/", func(c *gin.Context) {	// timing page
		// c.JSON(200, gin.H{
		// 	"message": "main page",
		// })
		c.HTML(200, "index.html", nil)
	})

	r.GET("/stat", func(c *gin.Context) {	// statics page
		c.JSON(200, gin.H{
			"message": "statistics page",
		})
	})

	r.GET("/backup", func(c *gin.Context) {	// backup page
		c.JSON(200, gin.H{
			"message": "backup page",
		})
	})

	r.Run() // listen and serve on 0.0.0.0:8080
}
