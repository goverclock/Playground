package main

import (
	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"github.com/go-gl/glfw/v3.3/glfw"
)

func main() {

	// make windows transparent
	err := glfw.Init()
	if err != nil {
		panic(err)
	}
	defer glfw.Terminate()
	// glfw.WindowHint(glfw.Decorated, 0)
	// glfw.WindowHint(glfw.TransparentFramebuffer, glfw.True)
glfw.WindowHint(glfw.Resizable, 0)
glfw.WindowHint(glfw.Decorated, 0)

	a := app.New()
	w := a.NewWindow("haha")
	w.Resize(fyne.NewSize(200, 200))

	img := canvas.NewImageFromFile("./00.png")
	w.Canvas().SetContent(img)
	w.ShowAndRun()

	// drv := a.Driver()
	// if drv, ok := drv.(desktop.Driver); ok {
	// 	w := drv.CreateSplashWindow()

	// 	w.Resize(fyne.NewSize(300, 300))
	// 	// cir := canvas.NewCircle(color.White)
	// 	// cir.Resize(fyne.NewSize(100, 100))

	// 	img := canvas.NewImageFromFile("./00.png")
	// 	w.Canvas().SetContent(img)
	// 	w.ShowAndRun()
	// }
}
