#Emmy Apaloo 

def print_welcome():
    '''
    Print welcome message
    '''

    print("Welcome to Voronoi Diagram Generator!")


def get_gridsize():
    '''
    Print grid description
    '''

    print("We are using a 15 x 15 grid.")
    print("The rows are indexed from 0 through 14, top to bottom.")


def get_sites():
    '''
    Get sites from user

    Returns:
        sites (list): list of sites
    '''

    print("Time to enter the sites!")
    print("When you are done entering sites, enter an empty.")

    sites = []
    counter = 0

    while True:
        try:
            site = input(
                f"Input coordinates r, c for site {counter} (no spaces):  ")

            if len(site) == 0 or counter > 5:
                break

            # Convert string to tuple
            site = site.split(",")
            r = int(site[0])
            c = int(site[1])
            site = (r,c)
            
            # # Check if site is valid
            # if len(site) != 2:
            #     break

            # Check if site values are between 0 and 14
            if site[0] < 0 or site[0] > 14 or site[1] < 0 or site[1] > 14:
                print(
                    "Warning , bad coordinate; last input was ignored."
                )
                continue

            # Do not allow duplicated
            if site not in sites:
                sites.append(site)
                counter += 1
            else:
                print(
                    "Warning, you already created that site; last input was ignored."
                )
        except:
            print(
                "Warning, bad coordinate; last input was ignored."
            )
    return sites


def get_squared_distance(r1, c1, r2, c2):
    '''
    Get squared distance between two points

    Parameters:
        r1 (int): row of first point
        c1 (int): column of first point
        r2 (int): row of second point
        c2 (int): column of second point

    Returns:
        squared_distance (int): squared distance between two points
    '''
    return (r1 - r2)**2 + (c1 - c2)**2


def get_region(sites, r, c):
    region = 0

    # Minimum squared distance between (r, c) and the first site
    min_squared_distance = get_squared_distance(r, c, sites[0][0], sites[0][1])

    # Iterate through the remaining sites
    for i in range(1, len(sites)):
        squared_distance = get_squared_distance(r, c, sites[i][0], sites[i][1])

        # Check if squared distance is smaller than the minimum squared distance
        if squared_distance < min_squared_distance:
            # Update minimum squared distance
            min_squared_distance = squared_distance

            # Update region number
            region = i
    return region


def get_regions_dictionary(sites):
    '''
    Get regions dictionary

    Parameters:
        sites (list): list of sites

    Returns:
        region_dict (dict): dictionary of regions
    '''

    # Create dictionary
    region_dict = {}

    # Iterate through the grid
    for r in range(15):
        for c in range(15):
            # Populate dictionary
            region_dict[(r, c)] = get_region(sites, r, c)

    return region_dict


def print_dict_as_matrix(region_dict, sites):
    '''
    Print dictionary as matrix

    Parameters:
        region_dict (dict): dictionary of regions
        sites (list): list of sites
    '''

    for r in range(15):
        for c in range(15):
            if (r, c) in sites:
                # Print site number
                print("@", end=" ")
            else:
                print(region_dict[(r, c)], end=" ")
        print()


def main():
    '''
    Main function
    '''

    # Print welcome message
    print_welcome()

    # Print grid description
    print_grid_descritpion()

    # Get sites
    sites = get_sites()
    print(f"You are using these sites: {sites}")

    # Draw regions dictionary
    if sites:
        region_dict = get_regions_dictionary(sites)
        print_dict_as_matrix(region_dict, sites)


main()
