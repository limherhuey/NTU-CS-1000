# CZ1115 Mini Project Codebase

###  FILES
1. Prime.ipynb
    - initial data exploration to prepare for cleaning
    - extraction, curation, preparation, and cleaning of data
    - feature engineering
    
2. Sentiment Analysis.ipynb
    - combination and translation (from Portuguese to English) of review titles and messages
    - sentiment analysis performed on the reviews, yielding polarities ranging from -1 (negative sentiment) to 1 (positive sentiment)

3. Visualisation Response 1 seller_items_sold.ipynb
    - data exploration, analysis, and visualisation of all features against response 1 (seller_items_sold)

4. Visualisation Response 2 product_items_sold.ipynb
    - data exploration, analysis, and visualisation of all features against response 2 (product_items_sold)

5. Visualisation Response 3 product_rating.ipynb
    - data exploration, analysis, and visualisation of all features against response 3 (product_rating)

6. Visualisation Response 4 product_polarity.ipynb
    - data exploration, analysis, and visualisation of all features against response 4 (product_polarity)

7. Outliers.ipynb
    - extraction, visualisation, and analysis of outliers from the responses to gain insights from well-performing sellers and products

8. Machine Learning.ipynb
    - linear regression to predict responses 1, 2, and 3 using features identified to be useful during visualisation
        **response 4 was found to have too low a correlation with any feature to train a viable regression model
    - analysis of coefficients of various features in different models
