import xlsxwriter

workbook = xlsxwriter.Workbook("d:\IOT\Projects\Smart I'd\Futher\GUI_files\Presenter.xlsx")

worksheet_Room1 = workbook.add_worksheet('Room_1')
worksheet_Room2 = workbook.add_worksheet('Room_2')


print(workbook.sheetnames)

workbook.close()