from employee import Employee
class SalariedEmployee(Employee):
    def __init__(self, name, job_title, annual_pay_rate):
        super().__init__(name, job_title)
        self.__annual_pay_rate = annual_pay_rate

    @property
    def employee_type(self):
        return "salaried"

    def calculate_pay(self):
        # Assume bi-monthly pay (twice a month)
        return self.__annual_pay_rate / 24

