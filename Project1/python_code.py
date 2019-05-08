from requests import get

def convert_money(money_amount, from_currency, to_currency):

    response = get('https://api.exchangerate-api.com/v4/latest/{}'.format(from_currency)).json()

    return money_amount * float(response['rates'][to_currency])
