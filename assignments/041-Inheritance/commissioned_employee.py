from salaried_employee import SalariedEmployee
class CommissionedEmployee(SalariedEmployee):
    def __init__(self, name, job_title, annual_pay_rate, period_gross_sales):
        super().__init__(name, job_title, annual_pay_rate)
        self.__annual_pay_rate = annual_pay_rate
        self.__period_gross_sales = period_gross_sales

    @property
    def employee_type(self):
        return "commissioned"

    def calculate_pay(self):
        # Calculate salaried pay plus 5% of period gross sales
        salaried_pay = self.__annual_pay_rate / 24
        commission = 0.05 * self.__period_gross_sales
        return salaried_pay + commission
