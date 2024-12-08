// ===========Variables=========
let user = document.querySelector(".user")
let total_avis = 0;
let nbl = 0;
fetch('clients.txt')
  .then(response => {
    if (!response.ok) {
      throw new Error('Network response was not ok');
    }
    return response.text(); // Read the file as text
  })
  .then(data => {
    lignes = data.split('\r\n');
    lignes.pop()
    nbl = lignes.length
    lignes.forEach(element => {
        // ===========Create item=========
        const item = document.createElement('div')
        item.className = 'item'
        item.innerHTML = `<div class="col-1">
                      <div class="image">
                        <img src="img/user.jpg" alt="">
                      </div>
                      <p>Name: <span>${element.split(';')[0]}</span></p>
                    </div>
                    <div class="col-2">
                      <p class="rating">Rating: <span>${element.split(';')[1]}</span><i class="fa-solid fa-star"></i></p>
                      <p class="comment">Commentaire: <span>${element.split(';')[2]}.</span></p>
                    </div>`
        user.appendChild(item)
        total_avis += Number(element.split(';')[1])
        // ===========Create item=========
       
    });

    document.querySelector("h1.avis").innerHTML += `(La Moyenne <span style="color:#ffc800">${(total_avis/ nbl).toFixed(2)}</span><i class="fa-solid fa-star"></i>)`
    if((total_avis/ nbl).toFixed(2) >= 1 && (total_avis/ nbl).toFixed(2) < 2 || (total_avis/ nbl).toFixed(2) < 1 ){        
      document.querySelector(".result").innerHTML = `Malheuresement la moyenne indique que les client sont Très Dissatisfaits😑`;
    }
    else if((total_avis/ nbl).toFixed(2) >= 2  && (total_avis/ nbl).toFixed(2) < 3){
      document.querySelector(".result").innerHTML = `La moyenne indique que les client sont Dissatisfaits😑`;
    }
    else if((total_avis/ nbl).toFixed(2) >= 3  && (total_avis/ nbl).toFixed(2) < 4){
      document.querySelector(".result").innerHTML = `La moyenne indique que les client sont Neutres😑`;
    }
    else if((total_avis/ nbl).toFixed(2) >= 4  && (total_avis/ nbl).toFixed(2) < 5){
      document.querySelector(".result").innerHTML = `Félicitations la moyenne indique que les client sont Saisfaits🙂`;
    }
    else if((total_avis/ nbl).toFixed(2) >= 5 ){
      document.querySelector(".result").innerHTML = `Félicitations la moyenne indique que les client sont Très Satisafait🫡`;
    }
  })
  .catch(error => {
    console.error('There was a problem with the fetch operation:', error);
  });