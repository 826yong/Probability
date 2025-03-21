let currentRotation = 0;
let yourChips = 10000;

function showRule() {
    let rule = document.getElementById("rule");

    if (rule.innerHTML === "查看遊戲規則") {
        rule.innerHTML = "選擇一個 36 的因數，賭注輪盤譨轉到該因數的倍數";
    } else {
        rule.innerHTML = "查看遊戲規則";
    }
}

function showChips() {
    let chips = document.getElementById("wallet");
    if (chips.innerHTML === "CHIPS") {
        chips.innerHTML = yourChips;
    } else {
        chips.innerHTML = "CHIPS";
    }
}

function showSpin() {
    let number = document.getElementById("bet_num").value;
    let amount = document.getElementById("bet_amount").value;

    number = parseInt(number, 10);
    amount = parseInt(amount, 10);

    if (isNaN(amount) || amount <= 0) {
        window.alert("請輸入有效的下注金額");

        if (number > 36 || number < 1) {
            window.alert("請輸入 1 到 36 之間的數字");
        }

        if ((36 % number) != 0) {
            window.alert("賭注數字並非 36 的因數");
        }
        return;
    }

    if ((yourChips - amount) < 0 ) {
        let retry = window.confirm("籌碼不足! 是否要重新下注?");
        if (retry) {
            document.getElementById("bet_num").value = "";
            document.getElementById("bet_amount").value = "";
            return;
        } else {
            window.alert("遊戲結束!");
            return;
        }
    }

    let wheel = document.getElementById("wheel");
    let randomDegree = Math.floor(Math.random() * 360) + 360 * 5;
    currentRotation += randomDegree;
    wheel.style.transition = "transform 3s ease-out";
    wheel.style.transform = `rotate(${currentRotation}deg)`;

    setTimeout(() => {
        let finalDegree = currentRotation % 360;
        let randomNumber = Math.floor((36 - finalDegree / 10) % 36) + 1;

        if (!(randomNumber % number)) {
            let addChips = (number - 1) * amount;
            yourChips += addChips;
            window.alert(`${randomNumber} 恭喜賭贏! 籌碼增加 ${addChips}`);
        } else {
            yourChips -= amount;
            window.alert(`${randomNumber} 賭輸了! 籌碼減少 ${amount}`);
        }

        document.getElementById("wallet").innerHTML = yourChips;
        
    }, 3000);

}
