const prompt = require("prompt-sync")();

const rows = 3;
const cols = 3;

const SYMBOL_ROWS = {
    A: 2,
    B: 4,
    C: 6,
    D: 8
}

const SYMBOL_VALUES = {
    A: 1,
    B: 3,
    C: 5,
    D: 7
}


const deposit = () => {
    var exit = false;
    while (exit != true) {
        const amount = prompt("Enter a deposit amount: ");
        const numberDepsoitamount = parseFloat(amount);

        if (isNaN(numberDepsoitamount) || numberDepsoitamount <= 0) {
            console.log("Invalid deposit amount , try again.")
        }
        else if (numberDepsoitamount > 0) {
            exit = true;
            return numberDepsoitamount;
        }

    }

}

const getLines = () => {
    var exit = false;
    while (exit != true) {
        const lines = prompt("Enter a lines amount to bet on (1-3): ");
        const numberofLines = parseInt(lines);

        if (isNaN(numberofLines) || numberofLines <= 0 || numberofLines > 3) {
            console.log("Invalid number of lines , try again.")
        }
        else if (numberofLines > 0) {
            exit = true;
            return numberofLines;
        }
    }
}

const getBet = (balance, amtLines) => {

    while (true) {
        const bet = prompt("Enter the bet per line : ");
        const amtOfBet = parseFloat(bet);
        let total = balance / amtLines;
        if (amtOfBet > total) {
            console.log("Amount of bet is greater than balance available, try again.");
        }
        else if (amtOfBet <= 0) {
            console.log("Invalid bet amount, try again.")
        }
        else {
            return amtOfBet;
        }
    }

}

const spin = () => {
    const symbols = [];
    for (const [symbol, count] of Object.entries(SYMBOL_ROWS)) {
        for (let i = 0; i < count; i++) {
            symbols.push(symbol);
        }
    }

    const roll = [[], [], []];

    for (let i = 0; i < cols; i++) {
        const rollSymbols = [...symbols];
        for (let j = 0; j < rows; j++) {
            const random = Math.floor(Math.random() * rollSymbols.length);
            const selectedSym = rollSymbols[random];
            roll[i].push(selectedSym);
            rollSymbols.splice(random, 1);
        }
    }
    return roll;

}

const transpose = (rolled) => {
    const ROWS = [];
    for (let i = 0; i < rows; i++) {
        ROWS.push([]);
        for (let j = 0; j < cols; j++) {
            ROWS[i].push(rolled[j][i]);
        }
    }
    return ROWS;
}

const printRow = (rolled) => {
    for (const row of rolled) {
        if (row.length > 0) {
            let rowString = "";
            for (const [i, symbol] of row.entries()) {
                rowString += symbol;
                if (i != row.length - 1) {
                    rowString += " | ";
                }
            }
            console.log(rowString);
        }
    }
}

const getWinning = (transposed, bet, lines) => {
    let winnings = 0;

    for (let i = 0; i < lines; i++) {
        const symbols = transposed[i];
        let allsame = true;
        for (const symbol of symbols) {
            if (symbol != symbols[0]) {
                allsame = false;
                break;
            }
        }
        if (allsame) {
            winnings += bet * SYMBOL_VALUES[symbols[0]];
        }

    }

    return winnings;


}

let balance = deposit();
var exit = false;
while (exit != true) {
    console.log("Your balance is: $" + balance);
    const amtLines = getLines();
    const bet = getBet(balance, amtLines);
    balance -= bet * amtLines;
    const rolled = spin();
    const transposed = transpose(rolled);
    printRow(rolled);
    const win = getWinning(transposed, bet, amtLines);
    balance += win;
    console.log("You won : $" + win.toString());
    
    const playAgain = prompt("Do you want to play again?(y/n): ");
    if (playAgain != "y") break;
    
    if (balance <= 0) {
        console.log("You ran out of balance !!!");
        exit = true;
    }
}


