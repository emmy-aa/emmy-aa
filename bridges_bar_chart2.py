
# bridges_barchart.py
# Barb Wahl
# October 2022

from bridges.symbol_collection import * # provides SymbolCollection, our data structure
from bridges.bridges import *
from bridges.rectangle import *
from bridges.text import *
from bridges.color import *

max_rect_width = 300

def make_rectangle(width, height, x, y, color="red"):
    # draw a rectangle with lower-left corner at (locx, locy)
    newRectangle = Rectangle(w=width, h=height, locx=x, locy=y)
    newRectangle.fill_color = color
    
    return newRectangle

def make_label(x, y, text, color="black"):
    newLabel = Text()
    newLabel.set_anchor_location(x, y)
    newLabel.set_anchor_alignment("right", "bottom")
    newLabel.font_size = 10.0
    newLabel.stroke_width = 0.3
    newLabel.text = text
    newLabel.opacity = 1
    newLabel.stroke_color = color

    return newLabel

# rel_freq is a float in the range 0.0 to 1.0, a proportion of the whole
def make_percent_label(x, y, rel_freq):
    pct = round(rel_freq * 100.0, 1)
    text = str(pct) + "%"
    
    return make_label(x, y, text)

def make_title_label(text):
    lab = make_label(-110, 60, text)
    lab.set_anchor_alignment("left", "bottom")
    lab.font_size = 16.0
    lab.stroke_width = 0.5
    
    return lab

def make_barchart(title, label1, label2, freq1, freq2, color1="springgreen", color2="deeppink"):
    sc = SymbolCollection()
    sc.add_symbol(make_title_label(title))

    # freq1 and freq2 should not be negative; if they are, set them to 0 and print a warning
    if freq1 < 0:
        print("Warning: freq1 should be non-negative.")
    if freq2 < 0:
        print("Warning: freq2 should be non-negative.")
    freq1 = max(freq1, 0.0)
    freq2 = max(freq2, 0.0)
    
    # the width of each bar is determined by the ratio of frequency to total, and is scaled by
    # max_rect_width
    total_freq = freq1 + freq2
    width1 = max_rect_width * freq1 / total_freq
    width2 = max_rect_width * freq2 / total_freq
    
    rect_1 = make_rectangle(width1, 10, -110, 20, color1)
    sc.add_symbol(rect_1)
    
    rect_2 = make_rectangle(width2, 10, -110, 40, color2)
    sc.add_symbol(rect_2)

    label_1 = make_label(-120, 20, label1)
    sc.add_symbol(label_1)
    
    label_2 = make_label(-120, 40, label2)
    sc.add_symbol(label_2)
    
    label_3 = make_label(0, 0, f"Number of Rounds: {freq1+freq2}", "red")
    sc.add_symbol(label_3)
    # x1 is the coordinate for the right end of bar 1, and similarly for x2
    x1 = -110 + width1
    x2 = -110 + width2
    
    percent_1 = make_percent_label(x1 + 5, 20, freq1 / total_freq)
    percent_2 = make_percent_label(x2 + 5, 40, freq2 / total_freq)
    
    for percent_lab in [percent_1, percent_2]:
        percent_lab.set_anchor_alignment("left", "bottom")
        sc.add_symbol(percent_lab)
    
    return sc

def main():
    bridges = Bridges(98877, "Emmy", "202285661209")
    bridges.set_title("Creating a Barchart with a Symbol Collection")
    bridges.set_description('Visualize a two-category comparison in BRIDGES')

    # set up the arguments for creating the barchart
    chart_title = "Monty Hall Simulation Results"
    name_1 = "Switching"
    name_2 = "Not Switching"
    count_1 = 60  # some positive integer
    count_2 = 56  # another positive integer
    color_1 = "pink"   # can you find other valid color names on the web?
    color_2 = "purple"      # hint: https://www.w3.org/TR/css-color-3/#svg-color

    # create the barchart and visualize it on the web
    chart = make_barchart(chart_title, name_1, name_2, count_1, count_2, color_1, color_2)
    bridges.set_data_structure(chart)
    bridges.visualize()

if __name__ == "__main__":
    main()



