const displayedImage = document.querySelector('.displayed-img');
const thumbBar = document.querySelector('.thumb-bar');

const btn = document.querySelector('button');
const overlay = document.querySelector('.overlay');

/* Declaring the array of image filenames */
const imgArr = [
    "pic1.jpg",
    "pic2.jpg",
    "pic3.jpg",
    "pic4.jpg",
    "pic5.jpg"
]

/* Declaring the alternative text for each image file */
const imgAltArr = [
    "pic1.jpg",
    "pic2.jpg",
    "pic3.jpg",
    "pic4.jpg",
    "pic5.jpg"
]

/* Looping through images */
for (let i = 0; i < imgArr.length; i++) {
    const newImage = document.createElement('img');
    newImage.setAttribute('src', "images/" + imgArr[i]);
    newImage.setAttribute('alt', imgAltArr[i]);
    thumbBar.appendChild(newImage);
}

thumbBar.onclick = function (e) {
    let s = e.target.src;
    displayedImage.setAttribute("src", s);
}

/* Wiring up the Darken/Lighten button */
btn.onclick = function () {
    let curMode = btn.getAttribute("class");
    if(curMode === "dark") {
        btn.setAttribute("class", "light");
        btn.textContent = "Lighten";
        overlay.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
    } else {
        btn.setAttribute("class", "dark");
        btn.textContent = "Darken";
        overlay.style.backgroundColor = "rgba(0, 0, 0, 0)";
    }
}
